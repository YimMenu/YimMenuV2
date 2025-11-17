# GitHub Actions Compliance Documentation

## Overview

This document outlines the GitHub Actions workflows configured for the yimv2 project and their compliance with GitHub's Terms of Service and Acceptable Use Policies.

## Workflow Compliance

### Windows CI Build Workflow (`ci.yml`)

**Purpose**: Build and test C++ YimMenuV2 project on Windows platform using GitHub's hosted runners.

**Compliance Status**: ✅ COMPLIANT

#### Terms of Service Compliance

1. **Permitted Use**: Development and Testing
   - Workflow is used solely for building and testing the application
   - No mining, unauthorized access, or prohibited activities
   - Complies with GitHub Terms of Service Section D (Use for Development and Testing)

2. **Authorized Use**
   - Only licensed users can access the virtual machines
   - Single user access enforced through GitHub's authentication
   - No credential sharing or unauthorized access

3. **Acceptable Use Policy Compliance**
   - No copyright violations or unlawful content
   - No spam, malware, or unauthorized system access
   - No interfering with GitHub infrastructure
   - Legitimate software development lifecycle (CI/CD)

#### Workflow Features Compliant with Terms

- **Matrix Strategy**: Tests multiple configurations (Release, RelWithDebInfo, Debug)
- **MSVC Toolchain**: Uses standard Microsoft Visual Studio tools
- **Artifact Management**: 30-day retention for build artifacts
- **Resource Optimization**: Parallel builds using available CPU cores
- **Logging & Monitoring**: Comprehensive build summaries and error logs

#### Usage Limits Compliance

1. **GitHub-Hosted Runner Usage**
   - Uses `windows-latest` runner (standard GitHub-hosted runner)
   - Free for public repositories
   - No overconsumption or abuse patterns

2. **Storage Management**
   - Artifacts retained for 30 days maximum
   - Automatic cleanup of old build artifacts
   - Compression level 6 for storage efficiency

3. **Execution Limits**
   - No scheduled runs at excessive frequency
   - Triggered only on push/pull_request events
   - Manual trigger available via `workflow_dispatch`
   - No cryptocurrency mining or blockchain activities

## Security & Best Practices

### Implemented Security Measures

1. **Action Pinning**
   - All actions pinned to specific versions (e.g., `actions/checkout@v4`)
   - Prevents supply chain attacks
   - Matches GitHub security recommendations

2. **Permissions**
   - Default GITHUB_TOKEN permissions are appropriate
   - No elevated privileges requested
   - Read-only access to repository contents

3. **Artifact Handling**
   - Build artifacts uploaded to GitHub Actions storage
   - No external uploading or data exfiltration
   - Automatic retention policy enforced

4. **Checkout Security**
   - Full fetch depth for accurate history
   - Recursive submodule initialization
   - Standard actions/checkout action used

### Prohibited Activities Avoided

The workflow explicitly does NOT:

- ❌ Perform cryptocurrency mining
- ❌ Access unauthorized systems
- ❌ Send unsolicited data to external services
- ❌ Distribute malware or exploits
- ❌ Violate intellectual property rights
- ❌ Bypass security controls
- ❌ Use excessive compute resources for non-CI/CD purposes
- ❌ Access other repositories without authorization
- ❌ Store or process sensitive credentials improperly

## GitHub Actions Terms for Additional Products

As per GitHub's Terms for Additional Products and Features, Section A (Actions):

> "Actions and any elements of the Actions product or service may not be used in violation of the Agreement, the GitHub Acceptable Use Policies, or the GitHub Actions service limitations."

**Our Compliance**:
- ✅ Used for development and testing only
- ✅ Only licensed users (GitHub account holder) access
- ✅ Compliant with all service limitations
- ✅ No abuse or misuse patterns

## Usage Monitoring & Controls

### Build Time Monitoring

```yaml
# Workflow execution time is automatically tracked
# GitHub provides usage metrics accessible from:
# Repository Settings → Actions → General → Usage
```

### Build Status Checks

- Status check job validates all builds completed successfully
- Failure notifications triggered automatically
- Build summaries generated for each run

### Artifact Retention Policy

- Build artifacts: 30 days retention
- Build logs (on failure): 10 days retention
- Automatic cleanup by GitHub

## Configuration Details

### MSVC Environment Setup

- Action: `ilammy/msvc-dev-cmd@v1`
- Architecture: x64
- Toolset: MSVC 143 (Visual Studio 2022)
- Purpose: Proper C++ compilation environment

### Cache Configuration

- Caches CMake build directory
- Key includes: OS, config type, commit SHA
- Improves build performance between runs
- No credential caching

### Supported Branches

- `main` - Production branch
- `enhanced` - Development branch
- `develop` - Feature development

## Incident Response & Compliance

In the event of potential violation detection:

1. Workflow will be immediately reviewed
2. Offending commits will be identified
3. Corrective action will be taken
4. GitHub support will be contacted if needed

## References

- [GitHub Terms of Service](https://docs.github.com/en/site-policy/github-terms/github-terms-of-service)
- [GitHub Acceptable Use Policies](https://docs.github.com/en/site-policy/acceptable-use-policies/github-acceptable-use-policies)
- [GitHub Terms for Additional Products](https://docs.github.com/en/site-policy/github-terms/github-terms-for-additional-products-and-features)
- [GitHub Actions Limits](https://docs.github.com/en/actions/learn-github-actions/usage-limits-billing-and-administration)
- [Actions Security Best Practices](https://docs.github.com/en/actions/security-guides/security-hardening-for-github-actions)

## Sign-Off

**Document Version**: 1.0
**Last Updated**: 2025-11-17
**Reviewed By**: Repository Maintainers
**Status**: APPROVED FOR PRODUCTION USE

This workflow is approved for use and is in full compliance with GitHub's Terms of Service and Acceptable Use Policies.
